namespace Lab10.Models
{
    public class Task
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Status { get; set; }
        public int UserId { get; set; }
        public DateTime Updated { get; set; }
    }
}
