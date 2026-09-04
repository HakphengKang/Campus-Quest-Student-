# Campus Quest — Student

Campus Quest is a student-facing application to help learners discover, plan, and track campus activities, academic tasks, and social events. This repository contains the Student mobile/web client for Campus Quest.

## Overview

The Student client provides an intuitive interface for students to:

- Browse campus events, clubs, and activities
- Register or RSVP for events
- View personalized schedules and deadlines
- Receive notifications and reminders
- Track academic tasks and progress
- Connect with other students and groups

This README gives an entry-level description, setup instructions, and development notes so contributors and maintainers can get started quickly.

## Key Features

- Events feed with filtering and search
- Calendar view and schedule management
- Task/to‑do list with due dates and reminders
- User authentication and profile management
- Club and group pages with membership and messaging
- Offline support and local caching (if implemented)

## Installation (Local Development)

1. Clone the repository:

   git clone https://github.com/HakphengKang/Campus-Quest-Student-.git
2. Change into the project directory:

   cd Campus-Quest-Student-
3. Install dependencies:

   npm install
   # or
   yarn install
4. Create a .env file from the example and set API endpoints / keys:

   cp .env.example .env
   # edit .env to point to your backend
5. Run the app:

   npm start
   # or for React Native
   npx react-native run-android
   npx react-native run-ios

## Configuration

- .env.example contains environment variables required to run the app locally.
- Update API_BASE_URL, AUTH_CLIENT_ID, and any feature flags as needed.


## Member and role

Memory Guardian: Ngorn Vitou

Record Architect: Srey Sotheadara

Test Captain: Hakpheng Kang

Integration Captain / Presenter: Ty Pisoth

Integration Captain / Presenter: Chea Sideth

---
