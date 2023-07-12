def planificacion_tareas(costos):
    num_trabajadores = len(costos)
    num_tareas = len(costos[0])

    asignaciones = []
    trabajadores_seleccionados = set()

    for tarea in range(num_tareas):
        mejor_trabajador = None
        menor_costo = float('inf')

        for trabajador in range(num_trabajadores):
            if trabajador not in trabajadores_seleccionados:
                costo = costos[trabajador][tarea]
                if costo < menor_costo:
                    mejor_trabajador = trabajador
                    menor_costo = costo

        asignaciones.append((mejor_trabajador, tarea))
        trabajadores_seleccionados.add(mejor_trabajador)

    costo_total = sum(costos[trabajador][tarea] for trabajador, tarea in asignaciones)

    return asignaciones, costo_total

# Ejemplo de costos de tareas
costos = [
    [11, 12, 18, 40],
    [14, 15, 13, 22],
    [11, 17, 19, 23],
    [17, 14, 20, 28]
]

asignaciones, costo_total = planificacion_tareas(costos)

print("Asignaciones:")
for trabajador, tarea in asignaciones:
    print(f"Trabajador {trabajador+1} -> Tarea {tarea+1}")

print(asignaciones)
print("Costo total:", costo_total)
