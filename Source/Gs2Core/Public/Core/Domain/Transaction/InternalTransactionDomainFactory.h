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

#include "Core/Domain/Transaction/TransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/TransactionDomain.h"
#include "Core/Domain/Transaction/TransactionDomainFactory.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"

namespace Gs2::Core::Domain::Internal
{
	class GS2CORE_API FTransactionDomainFactory
	{
	public:
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)
		{
			return Gs2::Core::Domain::FTransactionDomainFactory::ToTransaction(
				GS2,
				[&](
					const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
				)
				{
					return ToTransaction(
						GS2,
						AccessToken,
						Result
					);
				},
				AccessToken,
				bAutoRun,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId
			);
		}

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			FString UserId,
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId
		)
		{
			return Gs2::Core::Domain::FTransactionDomainFactory::ToTransaction(
				GS2,
				[&GS2, UserId](
					const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
				)
				{
					return ToTransaction(
						GS2,
						UserId,
						Result
					);
				},
				UserId,
				bAutoRun,
				TransactionId,
				StampSheet,
				StampSheetEncryptionKeyId
			);
		}
		
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)
		{
			return Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
				GS2,
				[&](
					bool bAutoRun,
					FString TransactionId,
					FString StampSheet,
					FString StampSheetEncryptionKeyId
				)
				{
					return ToTransaction(
						GS2,
						AccessToken,
						bAutoRun,
						TransactionId,
						StampSheet,
						StampSheetEncryptionKeyId
					);
				},
				AccessToken,
				Result
			);
		}

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const FString UserId,
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)
		{
			return Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
				GS2,
				[&GS2, UserId](
					bool bAutoRun,
					FString TransactionId,
					FString StampSheet,
					FString StampSheetEncryptionKeyId
				)
				{
					return ToTransaction(
						GS2,
						UserId,
						bAutoRun,
						TransactionId,
						StampSheet,
						StampSheetEncryptionKeyId
					);
				},
				UserId,
				Result
			);
		}
		
		static FTransactionAccessTokenDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
			bool bAutoRun,
			FString NamespaceName,
			FString JobName
		)
		{
			return Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
				GS2,
				[&](
					bool bAutoRun,
					FString TransactionId,
					FString StampSheet,
					FString StampSheetEncryptionKeyId
				)
				{
					return ToTransaction(
						GS2,
						AccessToken,
						bAutoRun,
						TransactionId,
						StampSheet,
						StampSheetEncryptionKeyId
					);
				},
				AccessToken,
				bAutoRun,
				NamespaceName,
				JobName
			);
		}

		static FTransactionDomainPtr ToTransaction(
			const FGs2Ptr& GS2,
			const FString UserId,
			bool bAutoRun,
			FString NamespaceName,
			FString JobName
		)
		{
			return Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
				GS2,
				[&GS2, UserId](
					bool bAutoRun,
					FString TransactionId,
					FString StampSheet,
					FString StampSheetEncryptionKeyId
				)
				{
					return ToTransaction(
						GS2,
						UserId,
						bAutoRun,
						TransactionId,
						StampSheet,
						StampSheetEncryptionKeyId
					);
				},
				UserId,
				bAutoRun,
				NamespaceName,
				JobName
			);
		}
	};
}
