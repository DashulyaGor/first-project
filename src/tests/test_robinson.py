# test_robinson.py

import json
from maraton.models import SpaceMissionRequest, SuccessResponse, FailResponse, ErrorResponse
from maraton.robinson_cruise import solve_mission_from_request

# Пример входного JSON
request_json = '''
{
"mass_shuttle": 1000.0,
"mass_fuel_unit": 1.0,
"power_per_unit": 1000.0,
"oxygen_time": 864000,
"total_fuel": 7000,
"fuel_consumption": 3.0,
"bodies": [
    {
    "id": "planet1",
    "gravity_assists": [
        {
        "velocity_gain": 10000.0,
        "fuel_consumption": 40,
        "time_to_execute": 1095
        },
        {
        "velocity_gain": 24000.0,
        "fuel_consumption": 84,
        "time_to_execute": 2026
        }
    ]
    },
    {
    "id": "gas_giant",
    "gravity_assists": []
    }
],
"edges": [
    {
    "from": "start_point",
    "to": "planet1",
    "distance": 1000
    },
    {
    "from": "planet1",
    "to": "gas_giant",
    "distance": 1000
    },
    {
    "from": "gas_giant",
    "to": "rescue_point",
    "distance": 1000
    }
]
}
'''

def test_from_json():
    try:
        # === 1. Загружаем JSON в словарь ===
        data = json.loads(request_json)

        # === 2. Создаём Pydantic-модель (автоматическая валидация) ===
        request = SpaceMissionRequest(**data)

        # После создания request
        print("Start point:", request.start_point)
        print("Rescue point:", request.rescue_point)
        print("Edges:", [(e.from_point, e.to, e.distance) for e in request.edges])
        print("Body gravity assists:", [(b.id, len(b.gravity_assists)) for b in request.bodies])

        # === 3. Вызов Cython-функции ===
        response = solve_mission_from_request(request)

        # === 4. Сериализуем в JSON ===
        if isinstance(response, SuccessResponse):
            print("Status: 200 OK")
            print(json.dumps(response.model_dump(), indent=2))
        elif isinstance(response, FailResponse):
            print("Status: 200 OK")
            print(json.dumps(response.model_dump(), indent=2))
        elif isinstance(response, ErrorResponse):
            print("Status: 400 Bad Request")
            print(json.dumps(response.model_dump(), indent=2))

    except Exception as e:
        print("Status: 400 Bad Request")
        print(json.dumps(ErrorResponse(status="incorrect_input").model_dump(), indent=2))
        print(f"Error: {e}")

if __name__ == "__main__":
    test_from_json()