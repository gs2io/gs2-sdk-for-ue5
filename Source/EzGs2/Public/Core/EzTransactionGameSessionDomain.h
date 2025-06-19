// Copyright 2016-2025 Game Server Services, Inc. or its affiliates. All Rights Reserved.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the “Software”), to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions
// of the Software.
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#pragma once

#include "Core/Domain/Transaction/TransactionAccessTokenDomain.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Core::Domain
{
	class EZGS2_API FEzTransactionGameSessionDomain final :
		public TSharedFromThis<FEzTransactionGameSessionDomain>
	{
		Gs2::Core::Domain::FTransactionAccessTokenDomainPtr Domain;
		Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;
	public:
		FEzTransactionGameSessionDomain(
			Gs2::Core::Domain::FTransactionAccessTokenDomainPtr Domain,
			Gs2::UE5::Util::FGs2ConnectionPtr& ConnectionValue
		);
		virtual ~FEzTransactionGameSessionDomain() = default;
		
		class FWaitTask :
			public Gs2::Core::Util::TGs2Future<FEzTransactionGameSessionDomain>,
			public TSharedFromThis<FWaitTask>
		{
			TSharedPtr<FEzTransactionGameSessionDomain> Self;
			bool All;

		public:
			explicit FWaitTask(
				TSharedPtr<FEzTransactionGameSessionDomain> Self,
				bool All
			);

			virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<FEzTransactionGameSessionDomain>> Result
			) override;
		};
		friend FWaitTask;

		virtual TSharedPtr<FAsyncTask<FWaitTask>> Wait(
			bool All = false
		);
	};

    typedef TSharedPtr<FEzTransactionGameSessionDomain> FEzTransactionGameSessionDomainPtr;
}
