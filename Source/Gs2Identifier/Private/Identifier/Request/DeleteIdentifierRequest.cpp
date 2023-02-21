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

#include "Identifier/Request/DeleteIdentifierRequest.h"

namespace Gs2::Identifier::Request
{
    FDeleteIdentifierRequest::FDeleteIdentifierRequest():
        UserNameValue(TOptional<FString>()),
        ClientIdValue(TOptional<FString>())
    {
    }

    FDeleteIdentifierRequest::FDeleteIdentifierRequest(
        const FDeleteIdentifierRequest& From
    ):
        UserNameValue(From.UserNameValue),
        ClientIdValue(From.ClientIdValue)
    {
    }

    TSharedPtr<FDeleteIdentifierRequest> FDeleteIdentifierRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteIdentifierRequest> FDeleteIdentifierRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteIdentifierRequest> FDeleteIdentifierRequest::WithClientId(
        const TOptional<FString> ClientId
    )
    {
        this->ClientIdValue = ClientId;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteIdentifierRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteIdentifierRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FDeleteIdentifierRequest::GetClientId() const
    {
        return ClientIdValue;
    }

    TSharedPtr<FDeleteIdentifierRequest> FDeleteIdentifierRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteIdentifierRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithUserName(Data->HasField("userName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithClientId(Data->HasField("clientId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("clientId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteIdentifierRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField("userName", UserNameValue.GetValue());
        }
        if (ClientIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clientId", ClientIdValue.GetValue());
        }
        return JsonRootObject;
    }
}