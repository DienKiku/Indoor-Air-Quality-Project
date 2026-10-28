import 'package:flutter/material.dart';

class AlertScreen extends StatelessWidget {
  const AlertScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffF4F7FB),

      appBar: AppBar(
        title: const Text(
          "Alerts",
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold),
        ),

        centerTitle: true,

        backgroundColor: Colors.white,

        elevation: 0,
      ),

      body: Padding(
        padding: const EdgeInsets.all(18),

        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,

          children: [
            const Text(
              "Current Status",

              style: TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
            ),

            const SizedBox(height: 20),

            Container(
              padding: const EdgeInsets.all(20),

              decoration: BoxDecoration(
                color: Colors.green,

                borderRadius: BorderRadius.circular(20),
              ),

              child: const Row(
                children: [
                  Icon(Icons.check_circle, color: Colors.white),

                  SizedBox(width: 10),

                  Text(
                    "Air quality is good",

                    style: TextStyle(color: Colors.white, fontSize: 18),
                  ),
                ],
              ),
            ),

            const SizedBox(height: 30),

            const Text(
              "History",

              style: TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
            ),

            const SizedBox(height: 15),

            AlertItem(
              title: "PM2.5 High",
              time: "10:32 Today",
              color: Colors.orange,
            ),

            AlertItem(
              title: "Temperature High",
              time: "Yesterday 15:20",
              color: Colors.red,
            ),
          ],
        ),
      ),
    );
  }
}

class AlertItem extends StatelessWidget {
  final String title;
  final String time;
  final Color color;

  const AlertItem({
    required this.title,

    required this.time,

    required this.color,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.only(bottom: 12),

      padding: const EdgeInsets.all(18),

      decoration: BoxDecoration(
        color: Colors.white,

        borderRadius: BorderRadius.circular(20),
      ),

      child: Row(
        children: [
          Icon(Icons.warning, color: color),

          const SizedBox(width: 15),

          Column(
            crossAxisAlignment: CrossAxisAlignment.start,

            children: [
              Text(title, style: const TextStyle(fontWeight: FontWeight.bold)),

              Text(time),
            ],
          ),
        ],
      ),
    );
  }
}
