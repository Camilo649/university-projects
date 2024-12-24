from User.user_data import USERS
from typing import Dict, Any

def get_user_by_id(user_id: int) -> Dict[str, Any]:
    res_user = None
    for user in USERS:
        if user["id"] == user_id:
            res_user = user
            break
    return res_user

def is_valid_username(username: str) -> bool:
    return username in [user["username"] for user in USERS]