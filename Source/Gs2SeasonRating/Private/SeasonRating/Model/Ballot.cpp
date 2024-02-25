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

#include "SeasonRating/Model/Ballot.h"

namespace Gs2::SeasonRating::Model
{
    FBallot::FBallot():
        UserIdValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        SessionNameValue(TOptional<FString>()),
        NumberOfPlayerValue(TOptional<int32>())
    {
    }

    FBallot::FBallot(
        const FBallot& From
    ):
        UserIdValue(From.UserIdValue),
        SeasonNameValue(From.SeasonNameValue),
        SessionNameValue(From.SessionNameValue),
        NumberOfPlayerValue(From.NumberOfPlayerValue)
    {
    }

    TSharedPtr<FBallot> FBallot::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FBallot> FBallot::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FBallot> FBallot::WithSessionName(
        const TOptional<FString> SessionName
    )
    {
        this->SessionNameValue = SessionName;
        return SharedThis(this);
    }

    TSharedPtr<FBallot> FBallot::WithNumberOfPlayer(
        const TOptional<int32> NumberOfPlayer
    )
    {
        this->NumberOfPlayerValue = NumberOfPlayer;
        return SharedThis(this);
    }
    TOptional<FString> FBallot::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FBallot::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<FString> FBallot::GetSessionName() const
    {
        return SessionNameValue;
    }
    TOptional<int32> FBallot::GetNumberOfPlayer() const
    {
        return NumberOfPlayerValue;
    }

    FString FBallot::GetNumberOfPlayerString() const
    {
        if (!NumberOfPlayerValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NumberOfPlayerValue.GetValue());
    }

    TSharedPtr<FBallot> FBallot::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBallot>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
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
            ->WithNumberOfPlayer(Data->HasField("numberOfPlayer") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("numberOfPlayer", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FBallot::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (SeasonNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonName", SeasonNameValue.GetValue());
        }
        if (SessionNameValue.IsSet())
        {
            JsonRootObject->SetStringField("sessionName", SessionNameValue.GetValue());
        }
        if (NumberOfPlayerValue.IsSet())
        {
            JsonRootObject->SetNumberField("numberOfPlayer", NumberOfPlayerValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBallot::TypeName = "Ballot";
}