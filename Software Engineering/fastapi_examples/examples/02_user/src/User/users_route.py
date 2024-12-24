from typing import Dict, Any, Optional
from fastapi import APIRouter, HTTPException, status
from passlib.context import CryptContext
from User.user_methods import get_user_by_id, is_valid_username
from User.user_schemas import UserIn, UserOut, UserUpdate
from User.user_data import USERS

user_router = APIRouter()

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")


@user_router.get(
        "/{user_id}",
        responses={
            status.HTTP_404_NOT_FOUND: {
                "description": "User not found.",
                "content": {
                    "application/json": {
                        "example": {
                            "detail": "User not found."
                        }
                    }
                }
            }
        }
    )
async def get_user(user_id: int):
    res_user = None
    res_user = get_user_by_id(user_id=user_id)
    if not res_user:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, 
            detail="User not found."
        )
    return res_user
 
@user_router.get("/")
async def get_user_list(
    user_from: Optional[int] = 0, 
    user_to: Optional[int] = None
):
    return USERS[user_from:user_to]

@user_router.post(
    "/", 
    response_model=UserOut,
    status_code=status.HTTP_201_CREATED,
    responses={
        status.HTTP_400_BAD_REQUEST: {
            "description": "Entered an existing name.",
            "content": {
                "application/json": {
                    "example": {
                        "detail": "Name already exists."
                    }
                }
            }
        }
    }
)
async def create_user(new_user: UserIn) -> int:
    if is_valid_username(new_user.username):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Name already exists."
        )
    new_id = len(USERS) + 1
    hashed_password = pwd_context.hash(new_user.password)
    user_dict = new_user.dict()
    user_dict.update({"id": new_id, "password": hashed_password})
    USERS.append(user_dict)
    return UserOut(
        id=new_id, 
        name=new_user.name,
        username=new_user.username, 
        operation_result="Successfully created!"
    )

@user_router.put(
    "/{user_id}",
    status_code=status.HTTP_201_CREATED,
    response_model=UserOut,
    responses={
        status.HTTP_404_NOT_FOUND: {
            "description": "User not found.",
            "content": {
                "application/json": {
                    "example": {
                        "detail": "User not found."
                    }
                }
            }
        },
        status.HTTP_400_BAD_REQUEST: {
            "description": "Entered an existing name.",
            "content": {
                "application/json": {
                    "example": {
                        "detail": "Name already exists."
                    }
                }
            }
        }
    }
)
async def update_user(user_id: int, user_update: UserUpdate):
    user_dict = get_user_by_id(user_id=user_id)
    if not user_dict:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, 
            detail="User not found."
        )
    if user_update.username and is_valid_username(user_update.username):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="Name already exists."
        )
    if user_update.password:
        user_update.password = pwd_context.hash(user_update.password)
    update_data = user_update.dict(exclude_unset=True)
    user_dict.update(update_data)
    return UserOut(
        id=user_id, 
        name=user_dict["name"] + " " + user_dict["surname"],
        username=user_dict["username"],
        operation_result="Successfully updated!"
    )

@user_router.delete(
    "/{user_id}",
    status_code=status.HTTP_200_OK,
    responses={
        status.HTTP_404_NOT_FOUND: {
            "description": "User not found.",
            "content": {
                "application/json": {
                    "example": {
                        "detail": "User not found."
                    }
                }
            }
        }
    }
)
async def delete_user(user_id: int) -> str:
    user_dict = get_user_by_id(user_id=user_id)
    if not user_dict:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, 
            detail="User not found."
        )
    USERS.remove(user_dict)
    return "Successfully eliminated!"

@user_router.delete(
    "/",
    status_code=status.HTTP_200_OK
)
async def delete_all_users() -> str:
    USERS.clear()
    return "All users have been eliminated!"
