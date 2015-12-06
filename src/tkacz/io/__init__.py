""" This package contains the implementations for the classes in the tkacz.core.access package. """

#=======================================================================================================================
# Exceptions for ZipBundle and other resource loaders.
#=======================================================================================================================

class FileLoaderException( Exception ):
	pass

class MalformedFileException( FileLoaderException ):
	pass

class NewerFormatVersionException( FileLoaderException ):
	pass
