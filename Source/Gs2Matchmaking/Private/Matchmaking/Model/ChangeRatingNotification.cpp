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

#include "Matchmaking/Model/ChangeRatingNotification.h"

namespace Gs2::Matchmaking::Model
{

    TSharedPtr<FChangeRatingNotification> FChangeRatingNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeRatingNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FChangeRatingNotification> FChangeRatingNotification::WithRateValue(
        const TOptional<float> RateValue
    ) {
        RateValueValue = RateValue;
        return SharedThis(this);
    }
    TOptional<float> FChangeRatingNotification::GetRateValue() const
    {
        return RateValueValue;
    }

    TSharedPtr<FChangeRatingNotification> FChangeRatingNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeRatingNotification>()
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRateValue(Data->HasField("rateValue") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("rateValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>());
    }
}
