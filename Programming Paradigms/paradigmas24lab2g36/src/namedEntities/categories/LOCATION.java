package namedEntities.categories;

public final class LOCATION extends Category {
    private Double longitude;
    private Double latitude;

    public LOCATION() {
        super("LOCATION");
        this.longitude = 0.0;
        this.latitude = 0.0;
    }

    public void setLongitude(Double longitude) {
        this.longitude = longitude;
    }

    public void setLatitude(Double latitude) {
        this.latitude = latitude;
    }

    public Double getLongitude() {
        return longitude;
    }

    public Double getLatitude() {
        return latitude;
    }

    public void print() {
        System.out.println("longitud: " + longitude);
        System.out.println("latitud: " + latitude);
    }
}