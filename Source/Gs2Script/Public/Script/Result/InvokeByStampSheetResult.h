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
#include "../Model/Transaction.h"
#include "../Model/RandomStatus.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Script::Result
{
    class GS2SCRIPT_API FInvokeByStampSheetResult final : public TSharedFromThis<FInvokeByStampSheetResult>
    {
        TOptional<int32> CodeValue;
        TOptional<FString> ResultValue;
        TSharedPtr<Model::FTransaction> TransactionValue;
        TSharedPtr<Model::FRandomStatus> RandomStatusValue;
        TOptional<bool> AtomicCommitValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        TOptional<int32> ExecuteTimeValue;
        TOptional<int32> ChargedValue;
        TSharedPtr<TArray<FString>> OutputValue;
        
    public:
        
        FInvokeByStampSheetResult();
        FInvokeByStampSheetResult(
            const FInvokeByStampSheetResult& From
        );
        ~FInvokeByStampSheetResult() = default;

        TSharedPtr<FInvokeByStampSheetResult> WithCode(const TOptional<int32> Code);
        TSharedPtr<FInvokeByStampSheetResult> WithResult(const TOptional<FString> Result);
        TSharedPtr<FInvokeByStampSheetResult> WithTransaction(const TSharedPtr<Model::FTransaction> Transaction);
        TSharedPtr<FInvokeByStampSheetResult> WithRandomStatus(const TSharedPtr<Model::FRandomStatus> RandomStatus);
        TSharedPtr<FInvokeByStampSheetResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FInvokeByStampSheetResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);
        TSharedPtr<FInvokeByStampSheetResult> WithExecuteTime(const TOptional<int32> ExecuteTime);
        TSharedPtr<FInvokeByStampSheetResult> WithCharged(const TOptional<int32> Charged);
        TSharedPtr<FInvokeByStampSheetResult> WithOutput(const TSharedPtr<TArray<FString>> Output);

        TOptional<int32> GetCode() const;
        FString GetCodeString() const;
        TOptional<FString> GetResult() const;
        TSharedPtr<Model::FTransaction> GetTransaction() const;
        TSharedPtr<Model::FRandomStatus> GetRandomStatus() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;
        TOptional<int32> GetExecuteTime() const;
        FString GetExecuteTimeString() const;
        TOptional<int32> GetCharged() const;
        FString GetChargedString() const;
        TSharedPtr<TArray<FString>> GetOutput() const;

        static TSharedPtr<FInvokeByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FInvokeByStampSheetResult, ESPMode::ThreadSafe> FInvokeByStampSheetResultPtr;
}