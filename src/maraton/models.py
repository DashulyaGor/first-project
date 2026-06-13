### Models for requests and responses


from pydantic import BaseModel, Field, model_validator
from typing import List

#print("model_validator imported from:", model_validator)
#print("model_validator module:", model_validator.__module__)
#print("pydantic version:", end=" ")
#try:
    #import pydantic
    #print(pydantic.__version__)
#except Exception as e:
    #print("unknown", e)

# --- MODELS FOR REQUESTS (INPUT) ---
class GravityAssist(BaseModel):
    velocity_gain: float = Field(gt=0)
    fuel_consumption: float = Field(gt=0)
    time_to_execute: int = Field(gt=0)

class Body(BaseModel):
    id: str
    gravity_assists: List[GravityAssist] = []

class Edge(BaseModel):
    from_point: str = Field(..., alias="from")
    to: str
    distance: float = Field(gt=0)

class SpaceMissionRequest(BaseModel):
    mass_shuttle: float = Field(gt=0)
    mass_fuel_unit: float = Field(gt=0)
    power_per_unit: float = Field(gt=0)
    oxygen_time: int = Field(gt=0)
    total_fuel: int = Field(gt=0)
    fuel_consumption_per_sec: float = Field(gt=0, alias="fuel_consumption")

    bodies: List[Body]
    edges: List[Edge]

    start_point: str = ""
    rescue_point: str = ""

    @model_validator(mode='after')
    def set_start_and_rescue_points(self):
        if not self.edges:
            raise ValueError("At least one edge is required to determine start and rescue points")
        self.start_point = self.edges[0].from_point
        self.rescue_point = self.edges[-1].to
        return self

# --- MODELS FOR RESPONSES (OUTPUT) ---
class SuccessResponse(BaseModel):
    can_reach: bool = True
    min_flight_time: float
    route: List[str]

class FailResponse(BaseModel):
    can_reach: bool = False

class ErrorResponse(BaseModel):
    status: str = "incorrect_input"