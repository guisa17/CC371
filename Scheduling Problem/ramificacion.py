def calcular_costo_parcial(asignacion_parcial, costos):
    costo_parcial = sum(costos[trabajador][tarea] for tarea, trabajador in enumerate(asignacion_parcial))
    return costo_parcial

def generar_hijos(asignacion_actual, trabajadores_disponibles, costos):
    hijos = []

    tarea_actual = len(asignacion_actual)
    trabajador_actual = asignacion_actual[-1] if asignacion_actual else -1

    for trabajador in trabajadores_disponibles:
        if trabajador != trabajador_actual:
            hijo = asignacion_actual + [trabajador]
            hijos.append(hijo)

    return hijos

def podar(asignacion_actual, trabajadores_disponibles, costos, mejor_costo_total):
    costo_parcial = calcular_costo_parcial(asignacion_actual, costos)

    if costo_parcial > mejor_costo_total:
        return True

    num_tareas = len(costos[0])
    tarea_actual = len(asignacion_actual)

    if tarea_actual == num_tareas:
        if costo_parcial < mejor_costo_total:
            mejor_costo_total = costo_parcial
        return True

    return False

def planificacion_tareas_branch_and_bound(costos):
    num_trabajadores = len(costos)
    trabajadores_disponibles = set(range(num_trabajadores))
    mejor_asignacion = []
    mejor_costo_total = float('inf')

    cota_superior = 73  # Valor obtenido como cota superior en el pseudocódigo
    cota_inferior = 58  # Valor obtenido como cota inferior en el pseudocódigo

    lista_nodos_vivos = [([], trabajadores_disponibles)]

    while lista_nodos_vivos:
        asignacion_actual, trabajadores_disponibles = lista_nodos_vivos.pop(0)

        if podar(asignacion_actual, trabajadores_disponibles, costos, mejor_costo_total):
            continue

        hijos = generar_hijos(asignacion_actual, trabajadores_disponibles, costos)

        for hijo in hijos:
            if not podar(hijo, trabajadores_disponibles, costos, mejor_costo_total):
                lista_nodos_vivos.append((hijo, trabajadores_disponibles.copy()))

        if len(asignacion_actual) == num_trabajadores:
            costo_parcial = calcular_costo_parcial(asignacion_actual, costos)
            if costo_parcial < mejor_costo_total:
                mejor_costo_total = costo_parcial
                lista_nodos_vivos = [(asignacion_actual, trabajadores_disponibles) for asignacion_actual, trabajadores_disponibles in lista_nodos_vivos if calcular_costo_parcial(asignacion_actual, costos) <= mejor_costo_total]

    asignaciones = [(trabajador, tarea) for tarea, trabajador in enumerate(asignacion_actual)]

    return asignaciones, mejor_costo_total


# Ejemplo de costos de tareas
costos = [
    [11, 12, 18, 40],
    [14, 15, 13, 22],
    [11, 17, 19, 23],
    [17, 14, 20, 28]
]

asignaciones, costo_total = planificacion_tareas_branch_and_bound(costos)

print("Asignaciones:")
for trabajador, tarea in asignaciones:
    print(f"Trabajador {trabajador+1} -> Tarea {tarea+1}")

print("Costo total:", costo_total)
