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

#include "Distributor/Result/DistributeWithoutOverflowProcessResult.h"

namespace Gs2::Distributor::Result
{
    FDistributeWithoutOverflowProcessResult::FDistributeWithoutOverflowProcessResult():
        DistributeResourceValue(nullptr),
        ResultValue(TOptional<FString>())
    {
    }

    FDistributeWithoutOverflowProcessResult::FDistributeWithoutOverflowProcessResult(
        const FDistributeWithoutOverflowProcessResult& From
    ):
        DistributeResourceValue(From.DistributeResourceValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FDistributeWithoutOverflowProcessResult> FDistributeWithoutOverflowProcessResult::WithDistributeResource(
        const TSharedPtr<Model::FDistributeResource> DistributeResource
    )
    {
        this->DistributeResourceValue = DistributeResource;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeWithoutOverflowProcessResult> FDistributeWithoutOverflowProcessResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDistributeResource> FDistributeWithoutOverflowProcessResult::GetDistributeResource() const
    {
        if (!DistributeResourceValue.IsValid())
        {
            return nullptr;
        }
        return DistributeResourceValue;
    }

    TOptional<FString> FDistributeWithoutOverflowProcessResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FDistributeWithoutOverflowProcessResult> FDistributeWithoutOverflowProcessResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDistributeWithoutOverflowProcessResult>()
            ->WithDistributeResource(Data->HasField("distributeResource") ? [Data]() -> Model::FDistributeResourcePtr
                 {
                    if (Data->HasTypedField<EJson::Null>("distributeResource"))
                    {
                        return nullptr;
                    }
                    return Model::FDistributeResource::FromJson(Data->GetObjectField("distributeResource"));
                 }() : nullptr)
            ->WithResult(Data->HasField("result") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("result", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDistributeWithoutOverflowProcessResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DistributeResourceValue != nullptr && DistributeResourceValue.IsValid())
        {
            JsonRootObject->SetObjectField("distributeResource", DistributeResourceValue->ToJson());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        return JsonRootObject;
    }
}