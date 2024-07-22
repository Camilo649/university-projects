package app.namedEntities;

import java.util.List;
import java.io.Serializable;

import app.namedEntities.categories.Category;

public class NamedEntity implements Serializable {
    private String Name;
    private Category Category;
    private List<String> Topics;
    private List<String> KeyWords;
    private int counter;

    public NamedEntity(String Name, Category Category, List<String> Topics, List<String> KeyWords) {
        this.Name = Name;
        this.Category = Category;
        this.Topics = Topics;
        this.KeyWords = KeyWords;
        this.counter = 1;
    }

    public void incrementCounter() {
        this.counter++;
    }

    public void setCounter(int num) {
        this.counter = num;
    }

    public void setCategory(Category Category) {
        this.Category = Category;
    }

    public void addTopics(String Topic) {
        this.Topics.add(Topic);
    }

    public void addKeyWord(String KeyWord) {
        this.KeyWords.add(KeyWord);
    }

    public String getName() {
        return Name;
    }

    public Category getCategory() {
        return Category;
    }

    public List<String> getTopics() {
        return Topics;
    }

    public List<String> getKeywords() {
        return KeyWords;
    }

    public int getCounter() {
        return counter;
    }

    public void print() {
        System.out.println("label: " + Name);
        System.out.println("Category: " + Category.get_Category_id());
        System.out.println("Topics: " + Topics);
        System.out.println("KeyWord: " + KeyWords);
    }
}