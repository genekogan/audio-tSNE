import fnmatch
import os
import numpy as np
import librosa
from sklearn.manifold import TSNE
import json

def get_audio_files(path, extension):
	files = []
	for root, dirnames, filenames in os.walk(path):
	    for filename in fnmatch.filter(filenames, '*.'+extension):
	        files.append(os.path.join(root, filename))
	return files

def get_features(path):
	y, sr = librosa.load(path)
	y = y[0:sr]
	#S = librosa.feature.melspectrogram(y, sr=sr, n_mels=128)
	#S = librosa.feature.mfcc(y, sr=sr)
	#log_S = librosa.logamplitude(S, ref_power=np.max)
	S = librosa.feature.melspectrogram(y, sr=sr, n_mels=128)
	log_S = librosa.logamplitude(S, ref_power=np.max)
	mfcc = librosa.feature.mfcc(S=log_S, n_mfcc=13)
	delta_mfcc = librosa.feature.delta(mfcc)
	delta2_mfcc = librosa.feature.delta(mfcc, order=2)
	#mean_mfcc = np.mean(S, 1)
	#mean_mfcc = (mean_mfcc-np.mean(mean_mfcc))/np.std(mean_mfcc)
	#var_mfcc = np.var(S, 1)
	#var_mfcc = (var_mfcc-np.mean(var_mfcc))/np.std(var_mfcc)
	#feature_vector = np.concatenate((mean_mfcc, var_mfcc))
	feature_vector = np.concatenate((np.mean(mfcc,1), np.mean(delta_mfcc,1), np.mean(delta2_mfcc,1)))
	feature_vector = (feature_vector-np.mean(feature_vector))/np.std(feature_vector)
	return feature_vector
	
#files = get_audio_files("/Users/gene/audio/Sounds/Nature effects/", 'wav')
audio_path = '/Users/gene/Downloads/Drum Samples/'
files = get_audio_files(audio_path, 'wav')
feature_vectors = []
for i,f in enumerate(files):
	print "get: %d/%d = %s"%(i, len(files), f)
	#try:
	feat = get_features(f)
	feature_vectors.append({"file":f, "features":feat})
	#except:
	#	print "missed %s"%f
	
	
i’m not connected to the infosec community but i spent 2 days with @ioerror at @cis_india. even then the megalomania was apparent

if he had been a simple megalomaniac rather than a rapist, it would probably just continue
	

save_path = '/Users/Gene/Desktop/audiotsnetest.json'

model = TSNE(n_components=2, perplexity=30, verbose=2, angle=0.1).fit_transform([f["features"] for f in feature_vectors])


x_axis=model[:,0]
y_axis=model[:,1]
x_norm = (x_axis-np.min(x_axis)) / (np.max(x_axis) - np.min(x_axis))
y_norm = (y_axis-np.min(y_axis)) / (np.max(y_axis) - np.min(y_axis))

data = []
for i,f in enumerate(feature_vectors):
	data.append({"path":f["file"], "x":x_norm[i], "y":y_norm[i]})

with open(save_path, 'w') as outfile:
    json.dump(data, outfile)	
	
#','.join([str(v) for v in v3])