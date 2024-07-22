import requests
from datetime import date


def get_url(year):
    return f"https://nolaborables.com.ar/api/v2/feriados/{year}"


months = ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo', 'Junio',
          'Julio', 'Agosto', 'Septiembre', 'Octubre', 'Noviembre', 'Diciembre']
days = ['Lunes', 'Martes', 'Miércoles',
        'Jueves', 'Viernes', 'Sábado', 'Domingo']
# El valor None es para que el programa devuelva el próximo feriado sin importar el tipo
types = ['None', 'inamovible', 'trasladable', 'nolaborable', 'puente']


def day_of_week(day, month, year):
    return days[date(year, month, day).weekday()]


# Con el nuevo parámetro type en las funciones set_next() y fetch_holiday() puedo buscar un feriado con un tipo específico
class NextHoliday:

    def __init__(self):
        self.loading = True
        self.year = date.today().year
        self.holiday = None

    def set_next(self, holidays, type):
        now = date.today()
        today = {
            'day': now.day,
            'month': now.month
        }

        holiday = next(
            (h for h in holidays if (h['mes'] == today['month'] and h['dia'] > today['day'])
             or (h['mes'] > today['month']) and (type == 'None' or h['tipo'] == type)),
            holidays[0]
        )
        # Si no se pudo encontrar otro feriado en el año actual con el tipo especificado, se termina la ejecución del programa
        if holiday == holidays[0] and type != holiday['tipo'] and type != 'None':
            print(f"\n\033[1mYa no hay más días {type} en el año\033[0m")
            raise SystemExit

        self.loading = False
        self.holiday = holiday

    def fetch_holidays(self, type):
        response = requests.get(get_url(self.year))
        data = response.json()
        self.set_next(data, type)

    def render(self):
        if self.loading:
            print("Buscando...")
        else:
            print("Próximo feriado")
            print(self.holiday['motivo'])
            print("Fecha:")
            (day_of_week(self.holiday['dia'], self.holiday['mes'], self.year))
            print(self.holiday['dia'])
            print(months[self.holiday['mes'] - 1])
            print("Tipo:")
            print(self.holiday['tipo'])


if __name__ == "__main__":  # Para que solo se ejecute cuando se llama directamente a proximo_feriado.py
    next_holiday = NextHoliday()
    next_holiday.fetch_holidays(types[0])
    next_holiday.render()
