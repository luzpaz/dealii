// ---------------------------------------------------------------------
//
// Copyright (C) 2021 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------



// verify hanging node constraints on locally p-refined simplex mesh
//
// dofs will be enumerated as follows
//  scenario 1:    scenario 2:
//   6-------4      2---4---3
//   |\      |      |\      |
//   |  \    |      |  \    |
//   3   2   |      |   5   6
//   |    \  |      |    \  |
//   |      \|      |      \|
//   0---1---5      0-------1


#include <deal.II/dofs/dof_handler.h>
#include <deal.II/dofs/dof_tools.h>

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/tria.h>

#include <deal.II/hp/fe_collection.h>

#include <deal.II/lac/affine_constraints.h>

#include <deal.II/simplex/fe_lib.h>
#include <deal.II/simplex/grid_generator.h>

#include "../tests.h"

#include "hanging_nodes.h"


int
main()
{
  initlog();

  deallog.push("2d");
  {
    const unsigned int dim = 2;

    const auto subdivided_hyper_cube_with_simplices =
      [](Triangulation<dim> &tria) {
        GridGenerator::subdivided_hyper_cube_with_simplices(tria, 1);
      };

    test<dim>({0, 0},
              {0, 1},
              hp::FECollection<dim>(Simplex::FE_P<dim>(2),
                                    Simplex::FE_P<dim>(1)),
              subdivided_hyper_cube_with_simplices);
    test<dim>({0, 0},
              {0, 1},
              hp::FECollection<dim>(Simplex::FE_P<dim>(1),
                                    Simplex::FE_P<dim>(2)),
              subdivided_hyper_cube_with_simplices);
  }
  deallog.pop();
}
