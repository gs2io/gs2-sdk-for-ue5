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

#include "SeasonRating/Model/WrittenBallot.h"

namespace Gs2::SeasonRating::Model
{
    FWrittenBallot::FWrittenBallot():
        BallotValue(nullptr),
        GameResultsValue(nullptr)
    {
    }

    FWrittenBallot::FWrittenBallot(
        const FWrittenBallot& From
    ):
        BallotValue(From.BallotValue),
        GameResultsValue(From.GameResultsValue)
    {
    }

    TSharedPtr<FWrittenBallot> FWrittenBallot::WithBallot(
        const TSharedPtr<FBallot> Ballot
    )
    {
        this->BallotValue = Ballot;
        return SharedThis(this);
    }

    TSharedPtr<FWrittenBallot> FWrittenBallot::WithGameResults(
        const TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> GameResults
    )
    {
        this->GameResultsValue = GameResults;
        return SharedThis(this);
    }
    TSharedPtr<FBallot> FWrittenBallot::GetBallot() const
    {
        return BallotValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FGameResult>>> FWrittenBallot::GetGameResults() const
    {
        return GameResultsValue;
    }

    TSharedPtr<FWrittenBallot> FWrittenBallot::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWrittenBallot>()
            ->WithBallot(Data->HasField(ANSI_TO_TCHAR("ballot")) ? [Data]() -> Model::FBallotPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("ballot")))
                    {
                        return nullptr;
                    }
                    return Model::FBallot::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("ballot")));
                 }() : nullptr)
            ->WithGameResults(Data->HasField(ANSI_TO_TCHAR("gameResults")) ? [Data]() -> TSharedPtr<TArray<Model::FGameResultPtr>>
                {
                    auto v = MakeShared<TArray<Model::FGameResultPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("gameResults")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("gameResults")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("gameResults")))
                        {
                            v->Add(Model::FGameResult::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FGameResultPtr>>());
    }

    TSharedPtr<FJsonObject> FWrittenBallot::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BallotValue != nullptr && BallotValue.IsValid())
        {
            JsonRootObject->SetObjectField("ballot", BallotValue->ToJson());
        }
        if (GameResultsValue != nullptr && GameResultsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GameResultsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("gameResults", v);
        }
        return JsonRootObject;
    }

    FString FWrittenBallot::TypeName = "WrittenBallot";
}