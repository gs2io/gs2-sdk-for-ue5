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

#include "SeasonRating/Request/GetBallotByUserIdRequest.h"

namespace Gs2::SeasonRating::Request
{
    FGetBallotByUserIdRequest::FGetBallotByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SessionNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NumberOfPlayerValue(TOptional<int32>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FGetBallotByUserIdRequest::FGetBallotByUserIdRequest(
        const FGetBallotByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SeasonNameValue(From.SeasonNameValue),
        SessionNameValue(From.SessionNameValue),
        UserIdValue(From.UserIdValue),
        NumberOfPlayerValue(From.NumberOfPlayerValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithSessionName(
        const TOptional<FString> SessionName
    )
    {
        this->SessionNameValue = SessionName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithNumberOfPlayer(
        const TOptional<int32> NumberOfPlayer
    )
    {
        this->NumberOfPlayerValue = NumberOfPlayer;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetSeasonName() const
    {
        return SeasonNameValue;
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetSessionName() const
    {
        return SessionNameValue;
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FGetBallotByUserIdRequest::GetNumberOfPlayer() const
    {
        return NumberOfPlayerValue;
    }

    FString FGetBallotByUserIdRequest::GetNumberOfPlayerString() const
    {
        if (!NumberOfPlayerValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NumberOfPlayerValue.GetValue());
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetBallotByUserIdRequest>()
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
            ->WithSeasonName(Data->HasField("seasonName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("seasonName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSessionName(Data->HasField("sessionName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("sessionName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithNumberOfPlayer(Data->HasField("numberOfPlayer") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("numberOfPlayer", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetBallotByUserIdRequest::ToJson() const
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
        if (SeasonNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonName", SeasonNameValue.GetValue());
        }
        if (SessionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("sessionName", SessionNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NumberOfPlayerValue.IsSet())
        {
            JsonRootObject->SetNumberField("numberOfPlayer", NumberOfPlayerValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}