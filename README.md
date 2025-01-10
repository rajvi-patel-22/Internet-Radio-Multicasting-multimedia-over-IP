# Internet Radio Multicasting (Multimedia over IP)

This project demonstrates **Internet Radio Multicasting**, a system designed to stream multimedia content (audio, video, etc.) over IP networks. Using multicast technology, this system can efficiently broadcast multimedia data to multiple clients simultaneously, reducing network congestion and enhancing user experience for large-scale broadcasting systems.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)

## Project Overview

The **Internet Radio Multicasting** project is designed to demonstrate how multimedia data can be transmitted over the Internet using multicast protocols. The project allows for the efficient delivery of multimedia content to multiple clients simultaneously, minimizing bandwidth usage compared to traditional unicast streaming.

### Key Highlights:
- **Multicasting Protocol**: Leverages the power of multicast transmission to stream audio/video data to multiple users without overloading the network.
- **Streaming Capability**: Capable of streaming audio content (Internet Radio) to clients using IP networks.
- **IP Networking**: Focuses on IP-based multimedia data transmission and includes considerations for packetizing, addressing, and stream management.
- **Scalability**: Designed to work efficiently even with a large number of clients.

## Features

- **Multicast Streaming**: Supports multicasting of multimedia content.
- **Audio Streaming**: Stream internet radio/audio to multiple users simultaneously.
- **Client Management**: Handles multiple client connections to receive multicast streams.
- **Error Handling**: Basic mechanisms to handle stream interruptions and retries.

## Technologies Used

- **Programming Language**: C (based on project implementation)
- **Networking Protocols**: UDP, Multicast
- **Audio Codec**: MP3, AAC, WAV (depending on the stream)
- **Libraries**: 
  - `socket` (for network communication)
  - `pyaudio` (for audio playback)
  - `ffmpeg` (for stream encoding and decoding)
