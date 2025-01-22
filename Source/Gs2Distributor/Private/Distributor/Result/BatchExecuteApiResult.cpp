/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Distributor/Result/BatchExecuteApiResult.h"

namespace Gs2::Distributor::Result
{
    FBatchExecuteApiResult::FBatchExecuteApiResult():
        ResultsValue(nullptr)
    {
    }

    FBatchExecuteApiResult::FBatchExecuteApiResult(
        const FBatchExecuteApiResult& From
    ):
        ResultsValue(From.ResultsValue)
    {
    }

    TSharedPtr<FBatchExecuteApiResult> FBatchExecuteApiResult::WithResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FBatchResultPayload>>> Results
    )
    {
        this->ResultsValue = Results;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBatchResultPayload>>> FBatchExecuteApiResult::GetResults() const
    {
        if (!ResultsValue.IsValid())
        {
            return nullptr;
        }
        return ResultsValue;
    }

    TSharedPtr<FBatchExecuteApiResult> FBatchExecuteApiResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBatchExecuteApiResult>()
            ->WithResults(Data->HasField(ANSI_TO_TCHAR("results")) ? [Data]() -> TSharedPtr<TArray<Model::FBatchResultPayloadPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FBatchResultPayloadPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("results")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("results")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("results")))
                        {
                            v->Add(Model::FBatchResultPayload::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBatchResultPayloadPtr>>());
    }

    TSharedPtr<FJsonObject> FBatchExecuteApiResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ResultsValue != nullptr && ResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("results", v);
        }
        return JsonRootObject;
    }
}