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

#include "Guild/Request/GetLastGuildMasterActivityByGuildNameRequest.h"

namespace Gs2::Guild::Request
{
    FGetLastGuildMasterActivityByGuildNameRequest::FGetLastGuildMasterActivityByGuildNameRequest():
        NamespaceNameValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        GuildNameValue(TOptional<FString>())
    {
    }

    FGetLastGuildMasterActivityByGuildNameRequest::FGetLastGuildMasterActivityByGuildNameRequest(
        const FGetLastGuildMasterActivityByGuildNameRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GuildModelNameValue(From.GuildModelNameValue),
        GuildNameValue(From.GuildNameValue)
    {
    }

    TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FGetLastGuildMasterActivityByGuildNameRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FGetLastGuildMasterActivityByGuildNameRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FGetLastGuildMasterActivityByGuildNameRequest::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FGetLastGuildMasterActivityByGuildNameRequest::WithGuildName(
        const TOptional<FString> GuildName
    )
    {
        this->GuildNameValue = GuildName;
        return SharedThis(this);
    }

    TOptional<FString> FGetLastGuildMasterActivityByGuildNameRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetLastGuildMasterActivityByGuildNameRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetLastGuildMasterActivityByGuildNameRequest::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TOptional<FString> FGetLastGuildMasterActivityByGuildNameRequest::GetGuildName() const
    {
        return GuildNameValue;
    }

    TSharedPtr<FGetLastGuildMasterActivityByGuildNameRequest> FGetLastGuildMasterActivityByGuildNameRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetLastGuildMasterActivityByGuildNameRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGuildModelName(Data->HasField(ANSI_TO_TCHAR("guildModelName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildModelName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGuildName(Data->HasField(ANSI_TO_TCHAR("guildName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetLastGuildMasterActivityByGuildNameRequest::ToJson() const
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
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
        }
        if (GuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildName", GuildNameValue.GetValue());
        }
        return JsonRootObject;
    }
}