using Org.BouncyCastle.Asn1.Cms;

namespace Lab10.Models
{
    public class Channels
    {
        public int Id { get; set; }
        public int PId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string Subscribers { get; set; }
    }
}
