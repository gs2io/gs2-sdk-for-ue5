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

#include "Guild/Request/SetMaximumCurrentMaximumMemberCountByGuildNameRequest.h"

namespace Gs2::Guild::Request
{
    FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::FSetMaximumCurrentMaximumMemberCountByGuildNameRequest():
        NamespaceNameValue(TOptional<FString>()),
        GuildNameValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        ValueValue(TOptional<int32>())
    {
    }

    FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::FSetMaximumCurrentMaximumMemberCountByGuildNameRequest(
        const FSetMaximumCurrentMaximumMemberCountByGuildNameRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GuildNameValue(From.GuildNameValue),
        GuildModelNameValue(From.GuildModelNameValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithGuildName(
        const TOptional<FString> GuildName
    )
    {
        this->GuildNameValue = GuildName;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithValue(
        const TOptional<int32> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetGuildName() const
    {
        return GuildNameValue;
    }

    TOptional<FString> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TOptional<int32> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetValue() const
    {
        return ValueValue;
    }

    FString FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ValueValue.GetValue());
    }

    TOptional<FString> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetMaximumCurrentMaximumMemberCountByGuildNameRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGuildName(Data->HasField("guildName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("guildName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGuildModelName(Data->HasField("guildModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("guildModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithValue(Data->HasField("value") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("value", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::ToJson() const
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
        if (GuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildName", GuildNameValue.GetValue());
        }
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}