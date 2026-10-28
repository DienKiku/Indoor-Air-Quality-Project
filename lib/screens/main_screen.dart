import 'package:flutter/material.dart';

import 'home_screen.dart';
import 'chart_screen.dart';
import 'alert_screen.dart';
import 'device_screen.dart';

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  int index = 0;

  final screens = [
    const HomeScreen(),

    const ChartScreen(),

    const AlertScreen(),

    const DeviceScreen(),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: screens[index],

      bottomNavigationBar: NavigationBar(
        selectedIndex: index,

        onDestinationSelected: (value) {
          setState(() {
            index = value;
          });
        },

        destinations: const [
          NavigationDestination(icon: Icon(Icons.home), label: "Home"),

          NavigationDestination(icon: Icon(Icons.bar_chart), label: "Chart"),

          NavigationDestination(
            icon: Icon(Icons.notifications),

            label: "Alert",
          ),

          NavigationDestination(icon: Icon(Icons.devices), label: "Device"),
        ],
      ),
    );
  }
}
