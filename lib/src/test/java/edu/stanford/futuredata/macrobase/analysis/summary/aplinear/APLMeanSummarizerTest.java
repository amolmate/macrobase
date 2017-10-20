package edu.stanford.futuredata.macrobase.analysis.summary.aplinear;

import edu.stanford.futuredata.macrobase.datamodel.DataFrame;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

import static junit.framework.TestCase.assertEquals;
import static org.junit.Assert.assertTrue;

public class APLMeanSummarizerTest {
    @Test
    public void testOrder3() throws Exception {
        DataFrame df = new DataFrame();
        String[] col1 = {"a1", "a2", "a1", "a1"};
        String[] col2 = {"b1", "b1", "b2", "b1"};
        String[] col3 = {"c1", "c1", "c1", "c2"};
        double[] counts = {100, 300, 400, 500};
        double[] means = {200.0, 20.0, 30.0, 25.0};
        double[] stdDevs = {15.0, 14.0, 13.0, 12.0};
        df.addStringColumn("col1", col1);
        df.addStringColumn("col2", col2);
        df.addStringColumn("col3", col3);
        df.addDoubleColumn("counts", counts);
        df.addDoubleColumn("means", means);
        df.addDoubleColumn("stdDevs", stdDevs);

        List<String> explanationAttributes = Arrays.asList(
                "col1",
                "col2",
                "col3"
        );
        APLMeanSummarizer summ = new APLMeanSummarizer();
        summ.setCountColumn("counts");
        summ.setMeanColumn("means");
        summ.setStdColumn("stdDevs");
        summ.setMinSupport(.05);
        summ.setMinStdDev(2.0);
        summ.setAttributes(explanationAttributes);
        summ.process(df);
        APLExplanation e = summ.getResults();
        assertEquals(1, e.getResults().size());
        assertTrue(e.prettyPrint().contains("col1=a1"));
    }
}