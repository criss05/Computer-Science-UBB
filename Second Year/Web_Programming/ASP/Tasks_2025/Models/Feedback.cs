namespace Lab10.Models
{
    public class Feedback
    {
        public int Id { get; set; }
        public int CustomerId { get; set; }
        public string Message { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
