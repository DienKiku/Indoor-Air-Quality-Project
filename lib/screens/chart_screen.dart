import 'package:flutter/material.dart';

class ChartScreen extends StatelessWidget {
  const ChartScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffF4F7FB),

      appBar: AppBar(
        title: const Text(
          "Data History",
          style: TextStyle(color: Colors.black, fontWeight: FontWeight.bold),
        ),

        centerTitle: true,

        backgroundColor: Colors.white,

        elevation: 0,
      ),

      body: SingleChildScrollView(
        padding: const EdgeInsets.all(18),

        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,

          children: [
            const Text(
              "Environmental Data",

              style: TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
            ),

            const SizedBox(height: 20),

            // chọn thông số
            Container(
              padding: const EdgeInsets.all(16),

              decoration: BoxDecoration(
                color: Colors.white,

                borderRadius: BorderRadius.circular(20),
              ),

              child: const Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,

                children: [
                  Text("Parameter"),

                  Text(
                    "PM2.5 ▼",
                    style: TextStyle(fontWeight: FontWeight.bold),
                  ),
                ],
              ),
            ),

            const SizedBox(height: 20),

            // chart giả lập
            Container(
              height: 250,

              padding: const EdgeInsets.all(20),

              decoration: BoxDecoration(
                color: Colors.white,

                borderRadius: BorderRadius.circular(25),
              ),

              child: CustomPaint(painter: ChartPainter(), child: Container()),
            ),

            const SizedBox(height: 20),

            Row(
              children: [
                Expanded(
                  child: _InfoCard(
                    title: "Average",

                    value: "0.035 mg/m³",

                    color: Colors.green,
                  ),
                ),

                const SizedBox(width: 15),

                Expanded(
                  child: _InfoCard(
                    title: "Maximum",

                    value: "0.062 mg/m³",

                    color: Colors.red,
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}

class _InfoCard extends StatelessWidget {
  final String title;
  final String value;
  final Color color;

  const _InfoCard({
    required this.title,

    required this.value,

    required this.color,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(18),

      decoration: BoxDecoration(
        color: Colors.white,

        borderRadius: BorderRadius.circular(20),
      ),

      child: Column(
        children: [
          Text(title),

          const SizedBox(height: 8),

          Text(
            value,

            style: TextStyle(
              fontSize: 20,

              fontWeight: FontWeight.bold,

              color: color,
            ),
          ),
        ],
      ),
    );
  }
}

class ChartPainter extends CustomPainter {
  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = Colors.green
      ..strokeWidth = 4
      ..style = PaintingStyle.stroke;

    Path path = Path();

    path.moveTo(0, size.height * 0.7);

    path.lineTo(50, size.height * 0.5);

    path.lineTo(100, size.height * 0.6);

    path.lineTo(160, size.height * 0.3);

    path.lineTo(220, size.height * 0.45);

    canvas.drawPath(path, paint);
  }

  @override
  bool shouldRepaint(CustomPainter oldDelegate) => false;
}
