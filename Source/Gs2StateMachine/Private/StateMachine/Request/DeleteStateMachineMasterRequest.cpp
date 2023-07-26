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

#include "StateMachine/Request/DeleteStateMachineMasterRequest.h"

namespace Gs2::StateMachine::Request
{
    FDeleteStateMachineMasterRequest::FDeleteStateMachineMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        VersionValue(TOptional<int64>())
    {
    }

    FDeleteStateMachineMasterRequest::FDeleteStateMachineMasterRequest(
        const FDeleteStateMachineMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        VersionValue(From.VersionValue)
    {
    }

    TSharedPtr<FDeleteStateMachineMasterRequest> FDeleteStateMachineMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStateMachineMasterRequest> FDeleteStateMachineMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteStateMachineMasterRequest> FDeleteStateMachineMasterRequest::WithVersion(
        const TOptional<int64> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteStateMachineMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteStateMachineMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int64> FDeleteStateMachineMasterRequest::GetVersion() const
    {
        return VersionValue;
    }

    FString FDeleteStateMachineMasterRequest::GetVersionString() const
    {
        if (!VersionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), VersionValue.GetValue());
    }

    TSharedPtr<FDeleteStateMachineMasterRequest> FDeleteStateMachineMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteStateMachineMasterRequest>()
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
            ->WithVersion(Data->HasField("version") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("version", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDeleteStateMachineMasterRequest::ToJson() const
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
        if (VersionValue.IsSet())
        {
            JsonRootObject->SetStringField("version", FString::Printf(TEXT("%lld"), VersionValue.GetValue()));
        }
        return JsonRootObject;
    }
}