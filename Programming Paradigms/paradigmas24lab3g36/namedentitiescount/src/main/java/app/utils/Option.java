package app.utils;

public class Option {
    private String name;
    private String longName;
    private Integer numValues;
    private Integer appearances;

    public Option(String name, String longName, Integer numValues) {
        this.name = name;
        this.longName = longName;
        this.numValues = numValues;
        this.appearances = 0;
    }

    public String getName() {
        return name;
    }

    public String getLongName() {
        return longName;
    }

    public Integer getnumValues() {
        return numValues;
    }

    public Integer getAppearances() {
        return appearances;
    }

    public void inc_numValues() {
        numValues++;
    }

    public void incAppearances() {
        appearances++;
    }
}
