open Query_Statement;

let select = Select.empty

let from = (t, table) => switch t {
| Select(r) => Select({...r, from: `From(Some(table))})
| Insert(_)
| Update(_)
| Delete(_) => t;
};

let columns = (t, columns) => switch t {
| Select(r) => Select({...r, columns: `Columns(columns)})
| Insert(_)
| Update(_)
| Delete(_) => t;
};

let where = (t: Query_Statement.t, column: string, operator: Query_Expression.operator) => {
  switch t {
  | Select(r) => {
      let `Where(expressions) = r.where;
      Select({ ...r, where: `Where([ Query_Expression.Single(column, operator),  ...expressions])});
    }
  | Update(r) => {
      let `Where(expressions) = r.where;
      Update({ ...r, where: `Where([ Query_Expression.Single(column, operator),  ...expressions])});
    }
  | Delete(r) => {
      let `Where(expressions) = r.where;
      Delete({ ...r, where: `Where([ Query_Expression.Single(column, operator),  ...expressions])});
    }
  | Insert(_) => t;
  };
}

let limit = (t: Query_Statement.t, number: int) => {
  switch t {
  | Select(r) => Select({...r, limit: `Limit(Some(number))})
  | Insert(_)
  | Update(_)
  | Delete(_) => t;
  };
}