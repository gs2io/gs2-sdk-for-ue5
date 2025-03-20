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

namespace Gs2::StateMachine::Model
{
    class GS2STATEMACHINE_API FStateMachineMaster final : public FGs2Object, public TSharedFromThis<FStateMachineMaster>
    {
        TOptional<FString> StateMachineIdValue;
        TOptional<FString> MainStateMachineNameValue;
        TOptional<FString> PayloadValue;
        TOptional<int64> VersionValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStateMachineMaster();
        FStateMachineMaster(
            const FStateMachineMaster& From
        );
        virtual ~FStateMachineMaster() override = default;

        TSharedPtr<FStateMachineMaster> WithStateMachineId(const TOptional<FString> StateMachineId);
        TSharedPtr<FStateMachineMaster> WithMainStateMachineName(const TOptional<FString> MainStateMachineName);
        TSharedPtr<FStateMachineMaster> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FStateMachineMaster> WithVersion(const TOptional<int64> Version);
        TSharedPtr<FStateMachineMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStateMachineMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FStateMachineMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStateMachineId() const;
        TOptional<FString> GetMainStateMachineName() const;
        TOptional<FString> GetPayload() const;
        TOptional<int64> GetVersion() const;
        FString GetVersionString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetVersionFromGrn(const FString Grn);

        static TSharedPtr<FStateMachineMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStateMachineMaster, ESPMode::ThreadSafe> FStateMachineMasterPtr;
}