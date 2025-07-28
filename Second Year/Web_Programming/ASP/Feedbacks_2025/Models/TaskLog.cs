namespace Lab10.Models
{
    public class TaskLog
    {
        public int Id { get; set; }
        public int TaskId { get; set; }
        public int UserId { get; set; }
        public string OldStatus { get; set; }
        public string NewStatus { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
