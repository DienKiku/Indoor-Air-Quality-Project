import 'package:flutter/material.dart';

class SensorCard extends StatelessWidget {
  final String title;
  final String value;
  final String unit;
  final IconData icon;
  final Color color;

  const SensorCard({
    super.key,

    required this.title,

    required this.value,

    required this.unit,

    required this.icon,

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
        crossAxisAlignment: CrossAxisAlignment.start,

        children: [
          Icon(icon, color: color),

          const SizedBox(height: 10),

          Text(title, style: const TextStyle(fontWeight: FontWeight.bold)),

          const Spacer(),

          Text(
            value,

            style: const TextStyle(fontSize: 28, fontWeight: FontWeight.bold),
          ),

          Text(unit),
        ],
      ),
    );
  }
}
