"""
Ejercicio sistema de votación para proyectos de Coding ULSA
"""
import tkinter as tk
from tkinter import messagebox


# Lista de proyectos participantes
proyectos = [
    "Proyecto A - App para Biblioteca",
    "Proyecto B - Plataforma de Tutorías",
    "Proyecto C - Control de Inventario",
    "Proyecto D - Sistema de Evaluaciones"
]

# Diccionario que cuenta los votos de un proyecto: {nombre_de_proyecto: num_votos}
votos = {proyecto: 0 for proyecto in proyectos}

def votar(seleccion: str):
    """
    Registrar voto del usuario
    :param seleccion: Nombre del Proyecto seleccionado por el usuario
    :return: None
    """
    votos [seleccion] += 1
    messagebox.showinfo(title=f"Votación", message=f"Se ha votado por la propuesta {seleccion}")

    # Votar y da feedback al usuario usando las funciones messagebox.showinfo y messagebox.showwarning
    pass

def mostrar_resultados():
    """
    Mostrar resultados de la votación
    :return: None
    """
    for numero_de_votos in votos:
        resultados = "\n".join(f"{proy}: {votos[proy]} voto(s)" for proy in proyectos)
    """estructura de control que en base a el proy que sea mayor en numero_de_votos imprima el ganador en una línea aparte, caso contrario o empate nada"""    
    messagebox.showinfo(title=f"Resultados", message=f"{resultados} {ganador}")
    
    # Calcular ganador y dar feedback al usuario con messagebox.showinfo

def main():
    root = tk.Tk()
    root.title("Sistema de Votación - Coding ULSA")
    root.geometry("500x400")
    root.configure(bg="#f0f0f0")

    # Titulo
    tk.Label(root, text="Sistema de Votación - Coding ULSA", font=("Arial", 16, "bold"), bg="#f0f0f0").pack(pady=20)

    # Variable para selección
    var = tk.StringVar()
    var.set(None)  # Inicializa la variable como None

    # Opciones de proyectos
    for proyecto in proyectos:
        tk.Radiobutton(root, text=proyecto, variable=var, value=proyecto, font=("Arial", 12), bg="#f0f0f0").pack(anchor="w", padx=50)

    # Botones
    btn_frame = tk.Frame(root, bg="#f0f0f0")
    btn_frame.pack(pady=20)

    tk.Button(btn_frame, text="Votar", command=lambda: votar(var.get()), width=15, bg="#4CAF50", fg="white", font=("Arial", 12)).grid(row=0, column=0, padx=10)
    tk.Button(btn_frame, text="Ver Resultados", command=mostrar_resultados, width=15, bg="#2196F3", fg="white", font=("Arial", 12)).grid(row=0, column=1, padx=10)
    tk.Button(btn_frame, text="Salir", command=root.quit, width=15, bg="#f44336", fg="white", font=("Arial", 12)).grid(row=0, column=2, padx=10)

    root.mainloop()

if __name__ == "__main__":
    main()