# multimedia_finder

Утилита для Linux на C++17, которая периодически обходит указанный каталог,
находит в нём мультимедийные файлы (аудио, видео, изображения) и формирует
отчёт в формате JSON.

Поддерживаются два режима выдачи отчёта:
- **JSON** (по умолчанию) — отчёт сохраняется в файл ~/.media_files.
- **HTTP** — отчёт доступен через GET `http://localhost:1234/media_files`,
  на файловую систему ничего не пишется.

## Зависимости

- CMake ≥ 3.16
- Компилятор с поддержкой C++17
- git (нужен CMake для FetchContent сторонних библиотек)

Сторонние библиотеки:

- [nlohmann/json](https://github.com/nlohmann/json) v3.11.3 — сериализация JSON
- [yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib) v0.41.0 — HTTP-сервер

## Сборка

```bash
cmake -B build
cmake --build build
```

## Запуск

```bash
./build/multimedia_finder [--dir <path>] [--interval <seconds>] [--report <json|http>]
```

### Аргументы по умолчанию

| Флаг | По умолчанию | Описание |
|---|---|---|
| --dir <path> | $HOME | Каталог для обхода (рекурсивно) |
| --interval <seconds> | 30 | Период повторного обхода в секундах |
| --report <json\|http> | json | Способ выдачи отчёта |

### Примеры

**JSON-режим** (отчёт пишется в ~/.media_files каждые 30 секунд):

```bash
./build/multimedia_finder
```

**JSON-режим с настройкой**: обходить ~/Music раз в 10 секунд:

```bash
./build/multimedia_finder --dir ~/Music --interval 10
```

**HTTP-режим**: поднять сервер на localhost:1234, обходить домашний каталог
каждые 5 секунд:

```bash
./build/multimedia_finder --interval 5 --report http
```

**Пример отчета**:

```json
{
  "audio": [
    "/home/user/Music/song.mp3",
    "/home/user/Music/track.wav"
  ],
  "video": [
    "/home/user/Videos/clip.mp4"
  ],
  "images": [
    "/home/user/Pictures/photo.jpg",
    "/home/user/Pictures/screen.png"
  ]
}
```

## Поддерживаемые форматы

Опознание идёт по расширению файла.

- **Аудио**: .mp3, .wav, .flac, .ogg, .aac, .m4a, .opus, .wma, .aiff, .ape
- **Видео**: .mp4, .mkv, .avi, .mov, .mpg, .mpeg, .flv, .webm, .wmv, .m4v, .3gp
- **Изображения**: .jpg, .jpeg, .png, .gif, .bmp, .webp, .tiff, .tif, .svg, .heic, .raw

## Остановка

Программа работает в бесконечном цикле. Для завершения — Ctrl+C в терминале
с запущенным процессом.
