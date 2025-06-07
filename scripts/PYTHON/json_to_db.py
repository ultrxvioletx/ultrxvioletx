import os
import json
import pandas as pd
from sqlalchemy import create_engine
from dotenv import load_dotenv


"""
json_to_db.py lee un archivo JSON ubicado en una ruta que se tiene que especificar y lo transforma en un dataframe de pandas, que posteriormente inserta en una base de datos.
Se utiliza recursividad para entrar dinámicamente a los distintos niveles, cualesquiera sean y sin importar la estructura;
si se encuentra con un arreglo creará una tabla correspondiente asociada a la principal mediante un id interno,
si se encuentra con un objeto simplemente agregará columnas a la tabla principal, concatenando los nombres para lograr mayor claridad y evitar duplicidad\sobreescritura.

@author Andrea Fernanda Rodríguez Rojas.
@version Julio 2024.
"""


#Variables globales
json_path = "/home/ultrxvioletx/Downloads/instagram/json/connections/followers_and_following/following.json"
main_name, ext = os.path.splitext(os.path.basename(json_path)) #nombre de la tabla principal, toma el nombre del archivo
data = {} #variable donde se almacena la data ya estructurada
temp_row = {} #variable temporal que almacena la información de la fila en proceso

# Creando la estructura, procesa variables de tipo diccionario
# String, Dict -> void
def _dict(table_name, row):
    for key, val in row.items():
        #De acuerdo el tipo de dato, manda la variable a la función correspondiente
        if isinstance(val, dict):
            _dict(table_name,val)
        elif isinstance(val, list):
            _list(key,val)

# Creando la estructura, procesa variables de tipo lista
# String, List -> void
def _list(table_name, rows):
    for row in rows:
        if isinstance(row, dict):
            _dict(table_name,row)
        data[table_name] = [] #se inicializa una nueva tabla debido a que hay una lista

# Creación de la estructura
# JSON -> void
def create_structure(_data):
    #De acuerdo el tipo de dato, manda la variable a la función correspondiente
    if isinstance(_data, list):
        _list(main_name,_data)
    elif isinstance(_data, dict):
        _list(main_name,[_data])

# Rellenando la data, procesa variables de tipo diccionario
# String, List, Int, Bool -> void
def _list_(table_name, rows, id, lvl0=False):
    for i,row in enumerate(rows):
        if (lvl0): id = i #en caso de que se trate del nivel base, se asigna el id interno que se mantendrá por todos los subniveles
        if isinstance(row, dict):
            _dict_(table_name,row,id)

# Rellenando la data, procesa variables de tipo lista
# String, List, Int, String -> void
def _dict_(table_name, row, id, parent=None):
    new_row = { 'id': id } #inicializa un diccionario correspondiente a una nueva fila
    
    for key,val in row.items():
        if isinstance(val, dict):
            globals()['temp_row'] = new_row #si hay un diccionario dentro, guarda la información ya procesada en una variable global
            _dict_(table_name,val,id,key)

        elif isinstance(val, list):
            globals()['temp_row'] = {} #si hay una lista dentro, reinicia la variable global para evitar sobreescritura
            _list_(key,val,id)

        else:
            if (key == 'id'): key = "id_" + table_name #si el json contiene un id le asigna otro nombre para evitar sobreescritura con el id interno
            if (parent is not None): key = parent + "_" + key #si hay una entidad padre asociada se concatenan los nombres para asignar a la columna
            new_row[key] = val #se agrega la propiedad y valor correspondientes a la fila

    if (parent is not None):
        globals()['temp_row'] |= new_row #si se procesó información de una entidad hija
                                        #se agrega la información a la variable global para que no se pierda al pasar de nivel
    else:
        new_row |= temp_row #si no hay (más) subniveles asociados se concatena la variable global que podría estar o no vacía
        data[table_name].append(new_row) #se agrega la fila a la tabla correspondiente en la data

# Relleno de información
# JSON -> void
def fill_data(_data):
    #De acuerdo el tipo de dato, manda la variable a la función correspondiente
    if isinstance(_data, list):
        _list_(main_name,_data,0,True)
    elif isinstance(_data, dict):
        _list_(main_name,[_data],0,True)


def main():
    #Abre y lee el archivo json
    with open(json_path, 'r') as file:
        _json = json.load(file)

    #Crea la estructura y rellena la información
    create_structure(_json)
    fill_data(_json)

    #Se traen las variables de entorno y se hace la conexión a la db
    load_dotenv()
    server = os.getenv('DB_SERVER')
    database = os.getenv('DB_DATABASE')
    username = os.getenv('DB_USERNAME')
    password = os.getenv('DB_PASSWORD')
    engine = create_engine(f'mssql+pymssql://{username}:{password}@{server}:1433/{database}')

    #Creación de las tablas de acuerdo a la data procesada
    for key,val in data.items():
        df = pd.DataFrame(val)
        df.to_sql(key, con=engine, if_exists="replace")
        print(f"Se creó la tabla {key}")

if __name__ == "__main__":
    main()