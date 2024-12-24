from fastapi import FastAPI, Request
from User.users_route import user_router

app = FastAPI(
    title="Example API",
    description="A simple user management API using FastAPI."
)

app.include_router(user_router, prefix="/users", tags=["Users"])

@app.get("/")
async def headers_example(request: Request):
    user_agent = request.headers.get("user-agent")
    return {"user_agent": user_agent}
