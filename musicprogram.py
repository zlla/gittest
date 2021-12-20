import webbrowser

class Playlist():
	def __init__(self, name, description, rating, videos):
		self.name = name
		self.description = description
		self.rating = rating
		self.videos = videos

class Video():
	def __init__(self, title, link):
		self.title = title
		self.link = link
	def open(self):
		webbrowser.open(self.link)

def read_video():
	title = input("Enter title video: ") + "\n" 
	link = input("Enter link video: ") + "\n"
	video = Video(title, link)
	return video

def print_video(video):
	print("Video title: ", video.title, end ="")
	print("Video Link: ", video.link, end ="")

def read_videos():
	videos = []
	total = select_in_range("Enter how many video: ", 20, 1)
	for i in range(total):
		print("Enter video " + str(i+1) + ": ")
		video = read_video()
		videos.append(video)
	return videos

def print_videos(videos):
	for i in range(len(videos)):
		print("Video " + str(i+1) + ": ")
		print_video(videos[i])

def write_video_txt(file, video):
	file.write(video.title)
	file.write(video.link)

def write_videos_txt(videos, file):
	total = len(videos)
	file.write(str(total) + "\n")
	for i in range(total):
		write_video_txt(file, videos[i])

def read_video_from_txt(file):
	title = file.readline()
	link = file.readline()
	video = Video(title, link)
	return video

def read_videos_from_txt(file):
	videos = []
	total = file.readline()
	total = int(total)
	for i in range(total):
		video = read_video_from_txt(file)
		videos.append(video)
	return videos

def read_playlist():
	playlist_name = input("Enter Playlist name: ") + "\n"
	playlist_description = input("Enter Playlist description: ") + "\n"
	playlist_rating = str(select_in_range("Enter Playlist rating(1-5): ", 5, 1)) + "\n"
	playlist_videos = read_videos()
	playlist = Playlist(playlist_name, playlist_description, playlist_rating, playlist_videos)
	return playlist

def write_playlist_txt(playlist):
	with open("data.txt", "w") as file:
		file.write(playlist.name)
		file.write(playlist.description)
		file.write(playlist.rating)
		write_videos_txt(playlist.videos, file)

def read_playlist_from_txt():
	with open("data.txt", "r") as file:
		playlist_name = file.readline()
		playlist_description = file.readline()
		playlist_rating = file.readline()
		playlist_videos = read_videos_from_txt(file)
		playlist = Playlist(playlist_name, playlist_description, playlist_rating, playlist_videos)
		return playlist

def print_playlist(playlist):
	print("------------")
	print("Playlist name: " + playlist.name, end ="")
	print("Playlist description: " + playlist.description, end="")
	print("Playlist rating: " + playlist.rating, end="")
	print_videos(playlist.videos)

def show_menu():
	print("---------------------------------")
	print("|           Main Menu           |")
	print("---------------------------------")
	print("|Option 1: Creat playlist       |")
	print("|Option 2: Show playlist        |")
	print("|Option 3: Play a video         |")
	print("|Option 4: Add a video          |")
	print("|Option 5: Update playlist      |")
	print("|Option 6: Remove a video       |")
	print("|Option 7: Save and Exit        |")
	print("---------------------------------")

def select_in_range(prompt, max, min):
	choice = input(prompt)
	while not choice.isdigit() or int(choice) > max or int(choice) < min:
		choice = input(prompt)
	choice = int(choice)
	return choice

def play_video(playlist):
	print_videos(playlist.videos)
	choice = select_in_range("Select a video(1 -> " + str(len(playlist.videos)) + "): ", len(playlist.videos), 1)
	print("Open video: " + playlist.videos[choice-1].title + "-" + playlist.videos[choice-1].link, end="")
	playlist.videos[choice-1].open()

def add_video(playlist):
	print("Enter new video information: ")
	new_video_title = input("Enter new title: ") + "\n"
	new_video_link = input("Enter new link: ") + "\n"
	new_video = Video(new_video_title, new_video_link)
	playlist.videos.append(new_video)

	return playlist

def update_playlist(playlist):
	# Update name / description / rating
	print("Update playlist?")
	print("1. Name")	
	print("2. Description")	
	print("3. Rating")	

	choice = select_in_range("Enter what you want to update (1-3): ", 3, 1)
	if choice == 1:
		new_playlist_name = input("Enter new name for playlist: ") + "\n"
		playlist.name = new_playlist_name
		print("Updated Successfully !")
		return playlist
	if choice == 2:
		new_playlist_description = input("Enter new description for playlist: ") + "\n"
		playlist.description = new_playlist_description
		print("Updated Successfully !")
		return playlist
	if choice == 3:
		new_playlist_rating = str(select_in_range("Enter new rating (1-5): ",1,5)) + "\n"
		playlist.rating = new_playlist_rating
		print("Updated Successfully !")
		return playlist

def remove_video(playlist):
	print_videos(playlist.videos)
	choice = select_in_range("Enter video you want to delete: ",len(playlist.videos) , 1)
	new_video_list = []
	# del playlist.videos[choice-1]
	for i in range(len(playlist.videos)):
		if i == choice-1:
			continue
		new_video_list.append(playlist.videos[i])

	playlist.videos = new_video_list

	print("Delete Successfully !!!")
	return playlist

def main():
	try:
		playlist = read_playlist_from_txt()
		print("Loaded data successfully!!!")
	except:
		print("Wellcome to first user!!!")
	while True:
		show_menu()
		choice = select_in_range("Select an option(1-7): ", 7, 1)
		if choice == 1:
			playlist = read_playlist()
			input("\nPress Enter to continue!")
		if choice == 2:
			print_playlist(playlist)
			input("\nPress Enter to continue!")
		if choice == 3:
			play_video(playlist)
			input("\nPress Enter to continue!")
		if choice == 4:
			playlist = add_video(playlist)
			input("\nPress Enter to continue.\n")
		if choice == 5:
			playlist = update_playlist(playlist)
			input("\nPress Enter to continue.\n")
		if choice == 6:
			playlist = remove_video(playlist)
			input("\nPress Enter to continue.\n")
		if choice == 7:
			write_playlist_txt(playlist)
			break
main()