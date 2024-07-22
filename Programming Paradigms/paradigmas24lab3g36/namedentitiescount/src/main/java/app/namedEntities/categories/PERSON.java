package app.namedEntities.categories;

public final class PERSON extends Category {
    private String formalName;
    private int age; // mayor a 0

    public PERSON() {
        super("PERSON");
        this.formalName = null;
        this.age = 0;
    }

    public void setFormalName(String formalName) throws Exception {
        if (formalName == null) {
            throw new Exception("nombre debe ser no null");
        }
        if (formalName.trim().isEmpty()) {
            throw new Exception("nombre no puede ser vacío");
        }
        this.formalName = formalName;
    }

    public void setAge(int Age) throws Exception {
        if (Age < 0) {
            throw new Exception("edad debe ser positiva");
        }
        this.age = Age;
    }

    public String getFormalName() {
        return formalName;
    }

    public int getAge() {
        return age;
    }

    public void print() {
        System.out.println("Nombre formal: " + formalName);
        System.out.println("Años: " + age);
    }
}