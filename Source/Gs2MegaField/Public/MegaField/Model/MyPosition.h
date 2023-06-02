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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "Position.h"
#include "Vector.h"

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FMyPosition final : public Gs2Object, public TSharedFromThis<FMyPosition>
    {
        TSharedPtr<FPosition> PositionValue;
        TSharedPtr<FVector> VectorValue;
        TOptional<float> RValue;

    public:
        FMyPosition();
        FMyPosition(
            const FMyPosition& From
        );
        virtual ~FMyPosition() override = default;

        TSharedPtr<FMyPosition> WithPosition(const TSharedPtr<FPosition> Position);
        TSharedPtr<FMyPosition> WithVector(const TSharedPtr<FVector> Vector);
        TSharedPtr<FMyPosition> WithR(const TOptional<float> R);

        TSharedPtr<FPosition> GetPosition() const;
        TSharedPtr<FVector> GetVector() const;
        TOptional<float> GetR() const;
        FString GetRString() const;


        static TSharedPtr<FMyPosition> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMyPosition, ESPMode::ThreadSafe> FMyPositionPtr;
}