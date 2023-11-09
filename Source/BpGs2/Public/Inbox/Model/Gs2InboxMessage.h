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
#include "Inbox/Domain/Model/Gs2InboxEzMessageGameSessionDomain.h"
#include "Inbox/Model/Gs2InboxAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2InboxMessage.generated.h"

USTRUCT(BlueprintType)
struct FGs2InboxOwnMessage
{
    GENERATED_BODY()

    Gs2::UE5::Inbox::Domain::Model::FEzMessageGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2InboxMessageValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString MessageId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    bool IsRead = false;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2InboxAcquireAction> ReadAcquireActions = TArray<FGs2InboxAcquireAction>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ReceivedAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ReadAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExpiresAt = 0;
};

inline FGs2InboxMessageValue EzMessageToFGs2InboxMessageValue(
    const Gs2::UE5::Inbox::Model::FEzMessagePtr Model
)
{
    FGs2InboxMessageValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxMessageFunctionLibrary::EzMessageToFGs2InboxMessageValue] Model parameter specification is missing."))
        return Value;
    }
    Value.MessageId = Model->GetMessageId() ? *Model->GetMessageId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.IsRead = Model->GetIsRead() ? *Model->GetIsRead() : false;
    Value.ReadAcquireActions = Model->GetReadAcquireActions() ? [&]
    {
        TArray<FGs2InboxAcquireAction> r;
        for (auto v : *Model->GetReadAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2InboxAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2InboxAcquireAction>();
    Value.ReceivedAt = Model->GetReceivedAt() ? *Model->GetReceivedAt() : 0;
    Value.ReadAt = Model->GetReadAt() ? *Model->GetReadAt() : 0;
    Value.ExpiresAt = Model->GetExpiresAt() ? *Model->GetExpiresAt() : 0;
    return Value;
}

inline Gs2::UE5::Inbox::Model::FEzMessagePtr FGs2InboxMessageValueToEzMessage(
    const FGs2InboxMessageValue Model
)
{
    return MakeShared<Gs2::UE5::Inbox::Model::FEzMessage>()
        ->WithMessageId(Model.MessageId)
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithIsRead(Model.IsRead)
        ->WithReadAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Inbox::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.ReadAcquireActions) {
                r->Add(FGs2InboxAcquireActionToEzAcquireAction(v));
            }
            return r;
        }())
        ->WithReceivedAt(Model.ReceivedAt)
        ->WithReadAt(Model.ReadAt)
        ->WithExpiresAt(Model.ExpiresAt);
}

UCLASS()
class BPGS2_API UGs2InboxMessageFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};