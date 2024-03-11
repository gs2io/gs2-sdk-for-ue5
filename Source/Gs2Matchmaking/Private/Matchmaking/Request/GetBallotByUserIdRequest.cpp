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

#include "Matchmaking/Request/GetBallotByUserIdRequest.h"

namespace Gs2::Matchmaking::Request
{
    FGetBallotByUserIdRequest::FGetBallotByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        RatingNameValue(TOptional<FString>()),
        GatheringNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NumberOfPlayerValue(TOptional<int32>()),
        KeyIdValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FGetBallotByUserIdRequest::FGetBallotByUserIdRequest(
        const FGetBallotByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RatingNameValue(From.RatingNameValue),
        GatheringNameValue(From.GatheringNameValue),
        UserIdValue(From.UserIdValue),
        NumberOfPlayerValue(From.NumberOfPlayerValue),
        KeyIdValue(From.KeyIdValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
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

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithRatingName(
        const TOptional<FString> RatingName
    )
    {
        this->RatingNameValue = RatingName;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithGatheringName(
        const TOptional<FString> GatheringName
    )
    {
        this->GatheringNameValue = GatheringName;
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

    TSharedPtr<FGetBallotByUserIdRequest> FGetBallotByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
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

    TOptional<FString> FGetBallotByUserIdRequest::GetRatingName() const
    {
        return RatingNameValue;
    }

    TOptional<FString> FGetBallotByUserIdRequest::GetGatheringName() const
    {
        return GatheringNameValue;
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

    TOptional<FString> FGetBallotByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
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
            ->WithRatingName(Data->HasField("ratingName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("ratingName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGatheringName(Data->HasField("gatheringName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("gatheringName", v))
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
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
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
        if (RatingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("ratingName", RatingNameValue.GetValue());
        }
        if (GatheringNameValue.IsSet())
        {
            JsonRootObject->SetStringField("gatheringName", GatheringNameValue.GetValue());
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
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}