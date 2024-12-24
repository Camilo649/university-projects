from typing import Optional
from pydantic import BaseModel, EmailStr

class UserIn(BaseModel):
    name: str
    surname: str
    age: Optional[int] = None
    mail: EmailStr
    active: bool
    username: str
    password: str

class UserUpdate(BaseModel):
    name: Optional[str] = None
    surname: Optional[str] = None
    age: Optional[int] = None
    mail: Optional[EmailStr] = None
    active: Optional[bool] = None
    username: Optional[str] = None
    password: Optional[str] = None

class UserOut(BaseModel):
    id: int
    name: str
    username : str
    operation_result: str