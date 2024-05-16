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

#include "Distributor/Result/DistributeResult.h"

namespace Gs2::Distributor::Result
{
    FDistributeResult::FDistributeResult():
        DistributeResourceValue(nullptr),
        InboxNamespaceIdValue(TOptional<FString>()),
        ResultValue(TOptional<FString>())
    {
    }

    FDistributeResult::FDistributeResult(
        const FDistributeResult& From
    ):
        DistributeResourceValue(From.DistributeResourceValue),
        InboxNamespaceIdValue(From.InboxNamespaceIdValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FDistributeResult> FDistributeResult::WithDistributeResource(
        const TSharedPtr<Model::FDistributeResource> DistributeResource
    )
    {
        this->DistributeResourceValue = DistributeResource;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeResult> FDistributeResult::WithInboxNamespaceId(
        const TOptional<FString> InboxNamespaceId
    )
    {
        this->InboxNamespaceIdValue = InboxNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FDistributeResult> FDistributeResult::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<Model::FDistributeResource> FDistributeResult::GetDistributeResource() const
    {
        if (!DistributeResourceValue.IsValid())
        {
            return nullptr;
        }
        return DistributeResourceValue;
    }

    TOptional<FString> FDistributeResult::GetInboxNamespaceId() const
    {
        return InboxNamespaceIdValue;
    }

    TOptional<FString> FDistributeResult::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FDistributeResult> FDistributeResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDistributeResult>()
            ->WithDistributeResource(Data->HasField(ANSI_TO_TCHAR("distributeResource")) ? [Data]() -> Model::FDistributeResourcePtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("distributeResource")))
                    {
                        return nullptr;
                    }
                    return Model::FDistributeResource::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("distributeResource")));
                 }() : nullptr)
            ->WithInboxNamespaceId(Data->HasField(ANSI_TO_TCHAR("inboxNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("inboxNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResult(Data->HasField(ANSI_TO_TCHAR("result")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("result"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDistributeResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DistributeResourceValue != nullptr && DistributeResourceValue.IsValid())
        {
            JsonRootObject->SetObjectField("distributeResource", DistributeResourceValue->ToJson());
        }
        if (InboxNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("inboxNamespaceId", InboxNamespaceIdValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        return JsonRootObject;
    }
}