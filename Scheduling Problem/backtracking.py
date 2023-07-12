def backtrack(costos, asignacion_actual, trabajadores_disponibles, mejor_asignacion, mejor_costo_total):
    num_tareas = len(costos[0])

    if len(asignacion_actual) == num_tareas:
        costo_total = sum(costos[trabajador][tarea] for tarea, trabajador in enumerate(asignacion_actual))
        if costo_total < mejor_costo_total:
            mejor_costo_total = costo_total
            mejor_asignacion[:] = asignacion_actual[:]  # Actualizar mejor asignación
        return mejor_asignacion, mejor_costo_total

    for trabajador in trabajadores_disponibles:
        asignacion_actual.append(trabajador)
        trabajadores_disponibles.remove(trabajador)

        mejor_asignacion, mejor_costo_total = backtrack(
            costos, asignacion_actual, trabajadores_disponibles, mejor_asignacion, mejor_costo_total
        )

        asignacion_actual.pop()
        trabajadores_disponibles.add(trabajador)

    return mejor_asignacion, mejor_costo_total


def planificacion_tareas_backtracking(costos):
    num_trabajadores = len(costos)
    trabajadores_disponibles = set(range(num_trabajadores))
    mejor_asignacion = []
    mejor_costo_total = float('inf')

    mejor_asignacion, mejor_costo_total = backtrack(
        costos, [], trabajadores_disponibles, mejor_asignacion, mejor_costo_total
    )

    asignaciones = [(trabajador, tarea) for tarea, trabajador in enumerate(mejor_asignacion)]

    return asignaciones, mejor_costo_total


# Ejemplo de costos de tareas
costos = [
    [11, 12, 18, 40],
    [14, 15, 13, 22],
    [11, 17, 19, 23],
    [17, 14, 20, 28]
]

asignaciones, costo_total = planificacion_tareas_backtracking(costos)

print("Asignaciones:")
for trabajador, tarea in asignaciones:
    print(f"Trabajador {trabajador+1} -> Tarea {tarea+1}")

print("Costo total:", costo_total)
