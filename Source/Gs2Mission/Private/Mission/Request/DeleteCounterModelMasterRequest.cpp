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

#include "Mission/Request/DeleteCounterModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FDeleteCounterModelMasterRequest::FDeleteCounterModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        CounterNameValue(TOptional<FString>())
    {
    }

    FDeleteCounterModelMasterRequest::FDeleteCounterModelMasterRequest(
        const FDeleteCounterModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CounterNameValue(From.CounterNameValue)
    {
    }

    TSharedPtr<FDeleteCounterModelMasterRequest> FDeleteCounterModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCounterModelMasterRequest> FDeleteCounterModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCounterModelMasterRequest> FDeleteCounterModelMasterRequest::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteCounterModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteCounterModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteCounterModelMasterRequest::GetCounterName() const
    {
        return CounterNameValue;
    }

    TSharedPtr<FDeleteCounterModelMasterRequest> FDeleteCounterModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteCounterModelMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCounterName(Data->HasField("counterName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("counterName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteCounterModelMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (CounterNameValue.IsSet())
        {
            JsonRootObject->SetStringField("counterName", CounterNameValue.GetValue());
        }
        return JsonRootObject;
    }
}