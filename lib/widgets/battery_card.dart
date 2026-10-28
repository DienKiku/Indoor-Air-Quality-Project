import 'package:flutter/material.dart';

class BatteryCard extends StatelessWidget {
  final int percentage;

  const BatteryCard({super.key, required this.percentage});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: const EdgeInsets.all(18),

      decoration: BoxDecoration(
        color: Colors.white,

        borderRadius: BorderRadius.circular(20),
      ),

      child: Row(
        children: [
          const Icon(Icons.battery_full, color: Colors.green),

          const SizedBox(width: 15),

          Text(
            "Đang hoạt động        $percentage%",

            style: const TextStyle(fontWeight: FontWeight.bold),
          ),
        ],
      ),
    );
  }
}
