package namedEntities.categories;

public abstract class Category {
    private String Category_identifier;

    public Category(String Category_identifier) {
        this.Category_identifier = Category_identifier;
    }

    public abstract void print();

    public String get_Category_id() {
        return Category_identifier;
    }

    public void print_id() {
        System.out.println(Category_identifier);
    }
}