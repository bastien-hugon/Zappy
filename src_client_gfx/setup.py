##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## setup
##


from setuptools import setup, Extension


setup(
    name='socket',
    version='1.0',
    description='Module for python to use C socket',
    ext_modules=[
        Extension(
            'socket',
            sources=['module.c'],
            py_limited_api=True)
    ],
)