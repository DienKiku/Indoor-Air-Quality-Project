import 'package:flutter/material.dart';

class AQICard extends StatelessWidget {
  final String status;
  final bool isAlert;
  final String alertReason;

  const AQICard({
    super.key,
    required this.status,
    required this.isAlert,
    required this.alertReason,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,

      padding: const EdgeInsets.all(25),

      decoration: BoxDecoration(
        color: Colors.green,

        borderRadius: BorderRadius.circular(25),
      ),

      child: Column(
        children: [
          const Text(
            "CHẤT LƯỢNG KHÔNG KHÍ",

            style: TextStyle(color: Colors.white, fontSize: 18),
          ),

          const SizedBox(height: 15),

          Text(
            status == 'GOOD' ? 'Good' : status,

            style: const TextStyle(
              color: Colors.white,

              fontSize: 42,

              fontWeight: FontWeight.bold,
            ),
          ),

          Text(
            isAlert
                ? alertReason
                : status == 'GOOD'
                    ? "Không khí trong lành"
                    : status,
            style: const TextStyle(color: Colors.white),
          ),
        ],
      ),
    );
  }
}
