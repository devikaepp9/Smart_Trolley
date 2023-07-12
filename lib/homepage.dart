import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

class Homepage extends StatefulWidget {
  const Homepage({super.key});

  @override
  State<Homepage> createState() => _HomepageState();
}

class _HomepageState extends State<Homepage> {
  @override
  Widget build(BuildContext context) {
    // DatabaseReference starCountRef =
    //     FirebaseDatabase.instance.ref('posts/starCount');
    // starCountRef.onValue.listen((DatabaseEvent event) {
    //   final data = event.snapshot.value;
    //   // updateStarCount(data);
    //   print("hi");
    //   print(data);
    // });

    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Smart Trolley',
        ),
      ),
      body: Container(
        child: const Text(
          'Hello guyss',
        ),
      ),
    );
  }
}
