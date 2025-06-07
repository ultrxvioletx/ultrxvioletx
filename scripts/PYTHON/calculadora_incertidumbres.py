import numpy as np
import sympy as sp
import pandas as pd

file_name = '/home/ultrxvioletx/Documents/GitHub/Scripts/PYTHON/prueba.csv'
df, columns, sym_columns = None, [], []
formula, n_round = "", 0


def defop(expression):
    op = ""
    if (isinstance(expression, sp.Add)): op = "sum"
    elif (isinstance(expression, sp.Mul)): op = "prod"
    elif (isinstance(expression, sp.Pow)): op = "pow"
    elif (isinstance(expression, sp.Number)): op = "num"
    return op

def calculate_error(X, Y, op):
    expression, error = sp.Basic, sp.Basic
    if (op == "sum"):
        expression = sp.Add(X[0],Y[0])
        error = sp.sqrt(X[1]**2+Y[1]**2)
    elif (op == "prod"):
        expression = sp.Mul(X[0],Y[0])
        error = sp.sqrt((X[0]*Y[0])**2 * ((X[1]/X[0])**2 + (Y[1]/Y[0])**2))
    elif (op == "pow"):
        expression = sp.Pow(X[0],Y[0])
        error = sp.Abs(Y[0]*expression/X[0] * X[1])
    return expression, error

def apply_formula(x,y,op, lvl = 0):
    dx, dy = sp.Basic, sp.Basic
    fx, fy = defop(x), defop(y)
    
    if (fx == "num"):
        dx = 0
    elif (fx == ""):
        dx = sp.symbols("d"+str(x.free_symbols.pop()))
    elif (fx == "pow"):
        x, dx = apply_formula(x.args[0],x.args[1],fx,lvl+1)
    else:
        x_att = x.as_two_terms()
        x, dx = apply_formula(x_att[0],x_att[1],fx,lvl+1)

    if (fy == "num"):
        dy = 0
    elif (fy == ""):
        dy = sp.symbols("d"+str(y.free_symbols.pop()))
    elif (fy == "pow"):
        y, dy = apply_formula(y.args[0],y.args[1],fy,lvl+1)
    else:
        y_att = y.as_two_terms()
        y, dy = apply_formula(y_att[0],y_att[1],fy,lvl+1)

    operation, error = calculate_error((x,dx), (y,dy), op)
    if (lvl == 0):
        operation = df.apply(lambda row: operation.evalf(subs={sym_columns[i]: row.iloc[i] for i,col in enumerate(columns)}), axis=1)
        error = df.apply(lambda row: error.evalf(subs={sym_columns[i]: row.iloc[i] for i,col in enumerate(columns)}), axis=1)
        df[globals()['formula']] = operation
        df[globals()['formula']] = df[globals()['formula']].apply(lambda x: sp.N(x, n=n_round))
        df["d_"+globals()['formula']] = error
        df["d_"+globals()['formula']] = df["d_"+globals()['formula']].apply(lambda x: sp.N(x, n=n_round))
    
    return operation, error


def main():
    globals()['df'] = pd.read_csv(file_name, sep=';')
    print("Tus datos son:")
    print(df.head())

    esc = False
    while (not esc):
        globals()['columns'] = df.columns.tolist()
        globals()['sym_columns'] = [sp.symbols(col) for col in columns]
        globals()['formula'] = input("Presiona 0 para salir, de lo contrario ingresa la formula: ")

        if (globals()['formula'] == "0"):
            esc = True
            break
        else:
            globals()['r'] = int(input("Cifras despues del punto decimal: "))
            expression = sp.sympify(formula)
            op = defop(expression)
            if (op == "pow"):
                apply_formula(expression.args[0],expression.args[1],op)
            else:
                att = expression.as_two_terms()
                apply_formula(att[0],att[1],op)
                
            print(df)


if __name__ == "__main__":
    main()