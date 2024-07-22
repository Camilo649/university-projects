package app.namedEntities.categories;

public final class ORGANIZATION extends Category {
    private String type;

    public ORGANIZATION() {
        super("ORGANIZATION");
        this.type = null;
    }

    public void setType(String type) throws Exception {
        if (type == null) {
            throw new Exception("tipo debe ser no null");
        }
        if (type.trim().isEmpty()) {
            throw new Exception("tipo no puede ser vacío");
        }
        this.type = type;
    }

    public String getType() {
        return type;
    }

    public void print() {
        System.out.println("tipo de organización: " + type);
    }
}